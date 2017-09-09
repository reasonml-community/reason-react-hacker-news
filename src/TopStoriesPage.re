open ReasonJs;

open Utils;

type state = {
  topstories: StoryData.topstories,
  page: int,
  loading: bool
};

type action =
  | Loaded (int, StoryData.topstories)
  | Loading
  | Scroll;

let component = ReasonReact.reducerComponent "TopStoriesPage";

let make _children => {
  let nearTheBottom () => distanceFromBottom () < 100;
  let loadNextPage {ReasonReact.state: state, reduce} =>
    if (state.page < 4) {
      StoryData.fetchTopStories state.page (reduce (fun payload => Loaded payload)) |> ignore;
      reduce (fun () => Loading) ()
    };
  {
    ...component,
    initialState: fun () => ({topstories: [||], page: 0, loading: false}: state),
    reducer: fun action state =>
      switch action {
      | Loading => ReasonReact.Update {...state, loading: true}
      | Loaded (page, data) =>
        let updatedTopstories = Array.concat [state.topstories, data];
        ReasonReact.Update {topstories: updatedTopstories, page: page + 1, loading: false}
      | Scroll =>
        ReasonReact.SideEffects (
          fun self =>
            if (nearTheBottom () && not self.state.loading) {
              loadNextPage self
            }
        )
      },
    didMount: fun self => {
      Dom.(Window.addEventListener "scroll" (self.reduce (fun _ => Scroll)) window);
      loadNextPage self;
      ReasonReact.NoUpdate
    },
    render: fun self => {
      let storyArray =
        if (Array.length self.state.topstories > 0) {
          Array.mapi
            (fun index story => <StoryListItem key=(string_of_int index) index story />)
            self.state.topstories
        } else {
          [||]
        };
      <div> (ReasonReact.arrayToElement storyArray) </div>
    }
  }
};
