open Utils;

requireCSS("src/CommentsPage.css");

type state = {story_with_comments: option(StoryData.story_with_comments)};

type action =
  | Loaded(StoryData.story_with_comments);

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
  {
    ...component,
    initialState: () => {story_with_comments: None},
    reducer: (action, _state) =>
      switch (action) {
      | Loaded(data) =>
        ReasonReact.Update({story_with_comments: Some(data)})
      },
    didMount: self =>
      StoryData.fetchStoryWithComments(id, data => self.send(Loaded(data))),
    render: ({state}) =>
      <MainLayout>
        <div className="CommentsPage_container">
          (
            switch (state.story_with_comments) {
            | Some(story) =>
              <div>
                (renderTitle(story))
                (renderByline(story))
                <CommentList story />
              </div>
            | None =>
              <div className="CommentsPage_loading">
                (ReasonReact.string("loading"))
              </div>
            }
          )
        </div>
      </MainLayout>,
  };
};
