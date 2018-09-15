open Utils;

requireCSS("src/CommentsPage.css");

type state = {
  loading: bool,
  story_with_comments: option(StoryData.story_with_comments),
  error: bool,
};

type action =
  | Loading
  | Loaded(StoryData.story_with_comments)
  | Error;

let component = ReasonReact.reducerComponent("CommentsPage");

let make = (~id, _children) => {
  let renderTitle = (story: StoryData.story_with_comments) => {
    let title =
      <h2 className="CommentsPage_title">
        (ReasonReact.string(story.title))
      </h2>;
    <div>
      (
        switch (story.url) {
        | Some(url) =>
          <a href=url className="CommentsPage_titleLink"> title </a>
        | None => title
        }
      )
    </div>;
  };
  let renderByline = (story: StoryData.story_with_comments) =>
    <div>
      <span> (ReasonReact.string(string_of_int(story.score))) </span>
      (ReasonReact.string(" points"))
      <span>
        <span>
          {
            let time = story.time;
            let by = story.by;
            ReasonReact.string({j| submitted $time by $by|j});
          }
        </span>
      </span>
    </div>;
  let loadStory = send => {
    StoryData.fetchStoryWithComments(id, result =>
      switch (result) {
      | Success(story) => send(Loaded(story))
      | Error => send(Error)
      }
    )
    |> ignore;
    send(Loading);
  };
  {
    ...component,
    initialState: () => {
      loading: false,
      story_with_comments: None,
      error: false,
    },
    reducer: (action, state) =>
      switch (action) {
      | Loading => ReasonReact.Update({...state, loading: true, error: false})
      | Loaded(story) =>
        ReasonReact.Update({
          ...state,
          loading: false,
          story_with_comments: Some(story),
        })
      | Error => ReasonReact.Update({...state, loading: false, error: true})
      },
    didMount: self => loadStory(self.send),
    render: ({state, send}) =>
      <div className="CommentsPage_container">
        (
          state.error ?
            <div className="message">
              (ReasonReact.string("Something went wrong... "))
              <a
                href="#"
                onClick=(
                  event => {
                    event |> ReactEventRe.Mouse.preventDefault;
                    loadStory(send);
                  }
                )>
                (ReasonReact.string("Click to retry"))
              </a>
            </div> :
            ReasonReact.null
        )
        (
          state.loading ?
            <div className="error">
              (ReasonReact.string("Loading..."))
            </div> :
            ReasonReact.null
        )
        (
          switch (state.story_with_comments) {
          | Some(story) =>
            <div>
              (renderTitle(story))
              (renderByline(story))
              <CommentList story />
            </div>
          | None => ReasonReact.null
          }
        )
      </div>,
  };
};